from iteration_utilities import deepflatten


def stripOp(left: list, operator: tuple, right: list):
    if operator[1] == '+' or operator[1] == '-':
        if len(right) == 1 and right[0] == ('num', '0'):
            return left
        elif len(left) == 1 and left[0] == ('num', '0'):
            return [operator, *right]
        else:
            newLeft = [('(', None)] + left + [(')', None)] if len(left) > 1 else left
            newRight = [('(', None)] + right + [(')', None)] if len(right) > 1 else right
            return [*newLeft, operator, *newRight]

    elif operator[1] == '*':
        if len(left) == 1 and left[0] == ('num', '0') or len(right) == 1 and right[0] == ('num', '0'):
            return [('num', '0')]
        elif len(left) == 1 and left[0] == ('num', '1'):
            return right
        elif len(right) == 1 and right[0] == ('num', '1'):
            return left
        else:
            newLeft = [('(', None)] + left + [(')', None)] if len(left) > 1 else left
            newRight = [('(', None)] + right + [(')', None)] if len(right) > 1 else right
            return [*newLeft, operator, *newRight]

    elif operator[1] == '/':
        if len(right) == 1 and right[0] == ('num', '0'):
            return None
        elif len(left) == 1 and left[0] == ('num', '0'):
            return [('num', '0')]
        elif len(right) == 1 and right[0] == ('num', '1'):
            return left
        else:
            newLeft = [('(', None)] + left + [(')', None)] if len(left) > 1 else left
            newRight = [('(', None)] + right + [(')', None)] if len(right) > 1 else right
            return [*newLeft, operator, *newRight]

    elif operator[1] == '^':
        if len(left) == 1 and left[0] == ('num', '1'):
            return ['num', '1']
        elif len(right) == 1 and right[0] == ('num', '0'):
            if len(left) == 1 and left[0] == ('num', '0'):
                return None
            else:
                return [('num', '1')]
        else:
            newLeft = [('(', None)] + left + [(')', None)] if len(left) > 1 else left
            newRight = [('(', None)] + right + [(')', None)] if len(right) > 1 else right
            return [*newLeft, operator, *newRight]


def findDerivative(tree: list, var: str) -> list:
    if len(tree) == 1 and (tree[0][0] == 'num' or tree[0][0] == 'const'):
        return [('num', '0')]

    elif len(tree) == 1 and tree[0][0] == 'var':
        return [('num', '0')] if tree[0][1] != var else [('num', '1')]

    elif len(tree) == 2:

        first = findDerivative(tree[1], var)

        if tree[0][1] == 'sin':
            return stripOp([('fun', 'cos'), *list(deepflatten(tree[1], types=list))], ('bin', '*'), first)

        elif tree[0][1] == 'cos':
            return stripOp([('num', '0')], ('bin1', '-'),
                           stripOp([('fun', 'sin'), *list(deepflatten(tree[1], types=list))], ('bin', '*'), first))

        elif tree[0][1] == 'tan':
            return stripOp(stripOp([('num', '1')], ('bin2', '/'),
                                   stripOp([('fun', 'cos'), *list(deepflatten(tree[1], types=list))],
                                           ('bin3', '^'), [('num', '2')])), ('bin2', '*'), first)

        elif tree[0][1] == 'cot':
            return stripOp([('num', '0')], ('bin1', '-'), stripOp(
                stripOp([('num', '1')], ('bin2', '/'),
                        stripOp([('fun', 'sin'), *list(deepflatten(tree[1], types=list))], ('bin3', '^'),
                                [('num', '2')])), ('bin2', '*'), first))

        elif tree[0][1] == 'asin':
            return stripOp(first, ('bin2', '/'), stripOp(
                stripOp([('num', '1')], ('bin1', '-'),
                        stripOp(list(deepflatten(tree[1], types=list)), ('bin3', '^'), [('num', '2')])),
                ('bin3', '^'), [('num', '0.5')]))

        elif tree[0][1] == 'acos':
            return stripOp([('num', '0')], ('bin1', '-'),
                           stripOp(first, ('bin2', '/'), stripOp(
                               stripOp([('num', '1')], ('bin1', '-'),
                                       stripOp(list(deepflatten(tree[1], types=list)), ('bin3', '^'),
                                               [('num', '2')])),
                               ('bin3', '^'), [('num', '0.5')])))

        elif tree[0][1] == 'atan':
            return stripOp(first, ('bin2', '/'), stripOp([('num', '1')], ('bin1', '+'),
                                                         stripOp(list(deepflatten(tree[1], types=list)),
                                                                 ('bin3', '^'), [('num', '2')])))

        elif tree[0][1] == 'acot':
            return stripOp([('num', '0')], ('bin1', '-'), stripOp(first, ('bin2', '/'),
                                                                  stripOp([('num', '1')], ('bin1', '+'),
                                                                          stripOp(
                                                                              list(deepflatten(tree[1], types=list)),
                                                                              ('bin3', '^'), [('num', '2')]))))

        elif tree[0][1] == 'ln':
            return stripOp(first, ('bin2', '/'), list(deepflatten(tree[1], types=list)))

        elif tree[0][1] == 'exp':
            return stripOp([('fun', 'exp'), *list(deepflatten(tree[1], types=list))], ('bin2', '*'), first)

    elif len(tree) == 3 and tree[0][0] == '(' and tree[2][0] == ')':
        inside = findDerivative(tree[1], var)
        return inside if len(inside) == 1 else [tree[0], *inside, tree[2]]

    elif len(tree) == 3:

        first = findDerivative(tree[0], var)
        second = findDerivative(tree[2], var)

        if tree[1][0] == 'bin1':
            return stripOp(first, tree[1], second)

        elif tree[1][1] == '*':
            return stripOp(stripOp(list(deepflatten(tree[0], types=list)), tree[1], second), ('bin1', '+'),
                           stripOp(list(deepflatten(tree[2], types=list)), tree[1], first))

        elif len(tree) == 3 and tree[1][1] == '/':
            return stripOp(
                stripOp(stripOp(list(deepflatten(tree[0], types=list)), ('bin2', '*'), second), ('bin1', '-'),
                        stripOp(list(deepflatten(tree[2], types=list)), ('bin2', '*'), first)), tree[1],
                stripOp(list(deepflatten(tree[2], types=list)), ('bin3', '^'), [('num', '2')]))

        elif len(tree) == 3 and tree[1][1] == '^':
            return stripOp(stripOp(
                stripOp(stripOp(list(deepflatten(tree[0], types=list)), ('bin3', '^'),
                                list(deepflatten(tree[2], types=list))), ('bin2', '*'),
                        second), ('bin2', '*'),
                [('fun', 'ln'), ('(', None), list(deepflatten(tree[0], types=list)), (')', None)]), ('bin1', '+'),
                stripOp(
                    stripOp(stripOp(list(deepflatten(tree[0], types=list)), ('bin3', '^'),
                                    stripOp(list(deepflatten(tree[2], types=list)), ('bin1', '-'), [('num', '1')])),
                            ('bin2', '*'),
                            first), ('bin2', '*'), list(deepflatten(tree[2], types=list)))
            )
