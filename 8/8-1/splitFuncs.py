from tokens import *


def splitBraces(tokenList: list) -> (list, bool):
    if tokenList[0][0] == '(' and tokenList[-1][0] == ')':
        return [('(', None), tokenList[1:-1], (')', None)], True
    return tokenList, False


def splitBinOperation(tokenList: list, priority: int) -> (list, bool):
    braceCounter = 0
    for i in range(len(tokenList)):
        if tokenList[i][0] == '(':
            braceCounter += 1
        elif tokenList[i][0] == ')':
            braceCounter -= 1
        elif tokenList[i][0] == 'bin' + str(priority):
            if braceCounter == 0:
                if priority == 1 and i == 0:
                    return [[('num', '0')], tokenList[i], tokenList[i + 1:]], True
                return [tokenList[:i], tokenList[i], tokenList[i + 1:]], True
    return tokenList, False


def splitFun(tokenList: list) -> (list, bool):
    if tokenList[0][1] in funDict:
        return [tokenList[0], tokenList[1:]], True
    return tokenList, False


def tokenListToTree(tokenList: list) -> list:
    result, isSplit = splitBinOperation(tokenList, 1)
    if isSplit:
        result[0] = tokenListToTree(result[0])
        result[-1] = tokenListToTree(result[-1])
        return result

    result, isSplit = splitBinOperation(tokenList, 2)
    if isSplit:
        result[0] = tokenListToTree(result[0])
        result[-1] = tokenListToTree(result[-1])
        return result

    result, isSplit = splitBinOperation(tokenList, 3)
    if isSplit:
        result[0] = tokenListToTree(result[0])
        result[-1] = tokenListToTree(result[-1])
        return result

    result, isSplit = splitFun(tokenList)
    if isSplit:
        result[1] = tokenListToTree(result[1])
        return result

    result, isSplit = splitBraces(tokenList)
    if isSplit:
        result[1] = tokenListToTree(result[1])
        return result

    return result
