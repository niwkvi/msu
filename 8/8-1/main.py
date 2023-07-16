from splitFuncs import *
from tokens import *
from derivative import *


with open('input.txt') as f:
    var = f.readline().strip()
    function = stringToTokens(f.readline().replace(' ', ''))

tree = tokenListToTree(function)
derivative = findDerivative(tree, var)

print(tokensToString(derivative))
