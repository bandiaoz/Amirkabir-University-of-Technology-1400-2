import re


def adjacentElementsProduct(inputArray):
    return max([inputArray[i] * inputArray[i + 1] for i in range(len(inputArray) - 1)])


def allLongestStrings(inputArray):
    return [i for i in inputArray if len(i) == len(max(inputArray, key=len))]


def checkPalindrome(inputString):
    return inputString == inputString[::-1]


def commonCharacterCount(s1, s2):
    return sum([min(s1.count(i), s2.count(i)) for i in set(s1)])


def areSimilar(A, B):
    return sorted(A) == sorted(B) and sum([a != b for a, b in zip(A, B)]) <= 2


def palindromeRearranging(inputString):
    return sum([inputString.count(i) % 2 for i in set(inputString)]) <= 1


def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [i if i != elemToReplace else substitutionElem for i in inputArray]


def evenDigitsOnly(n):
    return all([int(i) % 2 == 0 for i in str(n)])


def alphabeticShift(inputString):
    return "".join([chr(ord(i) + 1) if i != "z" else "a" for i in inputString])

def firstDigit(inputString):
    return int(re.findall("\d", inputString)[0])