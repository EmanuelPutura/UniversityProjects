# -*- coding: utf-8 -*-
from copy import deepcopy

from table import *


def computeValueForSet(table, setType, value):
    values = table[setType]
    result = 1
    if values['a'] is not None:
        result = min(result, (value - values['a']) / (values['b'] - values['a']))
    if values['c'] is not None:
        result = min(result, (values['c'] - value) / (values['c'] - values['b']))
    return max(result, 0)


def computeForAllSets(table, value):
    arr = {}
    for key in table.keys():
        arr[key] = computeValueForSet(table, key, value)
    return arr


def getAllCellsWithKey(fuzzyValues, key):
    arr = []
    for keyTheta in tableTheta.keys():
        for keyOmega in tableOmega.keys():
            if fuzzyRuleBase[keyTheta][keyOmega] == key:
                arr.append(fuzzyValues[keyTheta][keyOmega])
    return arr


def defuzzify(resultForce):
    numerator = 0
    denominator = 0
    for keyForce in resultForce.keys():
        numerator += resultForce[keyForce] * tableForce[keyForce]['b']
        denominator += resultForce[keyForce]
    if denominator == 0:
        return None
    return numerator / denominator


def solver(t, w):
    resultTheta = computeForAllSets(tableTheta, t)
    resultOmega = computeForAllSets(tableOmega, w)

    fuzzyRuleBaseCopy = deepcopy(fuzzyRuleBase)
    for keyTheta in resultTheta.keys():
        for keyOmega in resultOmega.keys():
            fuzzyRuleBaseCopy[keyTheta][keyOmega] = min(resultTheta[keyTheta], resultOmega[keyOmega])

    resultForce = {}
    for key in tableForce.keys():
        resultForce[key] = max(getAllCellsWithKey(fuzzyRuleBaseCopy, key))

    return defuzzify(resultForce)
