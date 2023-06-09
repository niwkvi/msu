from iteration_utilities import deepflatten

funDict = ['sin', 'cos', 'tan', 'cot',
           'asin', 'acos', 'atan', 'acot',
           'ln', 'exp']


def stringToTokens(expression: str) -> list | None:
    tokenList = []
    i = 0
    while i < len(expression):
        if expression[i] in ['(', ')']:
            tokenList.append((expression[i], None))
            i += 1
        elif expression[i] in ['+', '-']:
            tokenList.append(('bin1', expression[i]))
            i += 1
        elif expression[i] in ['*', '/']:
            tokenList.append(('bin2', expression[i]))
            i += 1
        elif expression[i] == '^':
            tokenList.append(('bin3', expression[i]))
            i += 1
        elif expression[i].isalpha():
            j = i + 1
            while j < len(expression) and expression[j].isalpha():
                j += 1
            word = expression[i:j]
            if word in ['e', 'pi']:
                tokenList.append(('const', word))
            elif len(word) == 1:
                tokenList.append(('var', word))
            elif word in funDict:
                tokenList.append(('fun', word))
            else:
                return None
            i = j
        elif expression[i].isdigit():
            j, flag = i + 1, False
            while j < len(expression):
                if expression[j].isdigit():
                    j += 1
                elif expression[j] == '.' and not flag:
                    j += 1
                    flag = True
                elif expression[j] == '.' and flag:
                    return None
                else:
                    break
            word = expression[i:j]
            tokenList.append(('num', word))
            i = j
    return tokenList


def tokensToString(tokenList: list) -> str:
    string = list(deepflatten(tokenList, types=list))
    for i in range(len(string)):
        if string[i][1] is not None:
            string[i] = string[i][1]
        else:
            string[i] = string[i][0]
    return ''.join(string)
