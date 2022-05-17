tableTheta = {
    'NVB': {
        'a': None,
        'b': -40,
        'c': -25
    },
    'NB': {
        'a': -40,
        'b': -25,
        'c': -10
    },
    'N': {
        'a': -20,
        'b': -10,
        'c': 0
    },
    'Z': {
        'a': -5,
        'b': 0,
        'c': 5
    },
    'P': {
        'a': 0,
        'b': 10,
        'c': 20
    },
    'PB': {
        'a': 10,
        'b': 25,
        'c': 40
    },
    'PVB': {
        'a': 25,
        'b': 40,
        'c': None
    }
}

tableOmega = {
    'NB': {
        'a': None,
        'b': -8,
        'c': -6
    },
    'N': {
        'a': -6,
        'b': -3,
        'c': 0
    },
    'Z': {
        'a': -1,
        'b': 0,
        'c': 1
    },
    'P': {
        'a': 0,
        'b': 3,
        'c': 6
    },
    'PB': {
        'a': 3,
        'b': 8,
        'c': None
    }
}

tableForce = {
    'NVVB': {
        'a': None,
        'b': -32,
        'c': -24
    },
    'NVB': {
        'a': -32,
        'b': -24,
        'c': -16
    },
    'NB': {
        'a': -24,
        'b': -16,
        'c': -8
    },
    'N': {
        'a': -16,
        'b': -8,
        'c': 0
    },
    'Z': {
        'a': -4,
        'b': 0,
        'c': 4
    },
    'P': {
        'a': 0,
        'b': 8,
        'c': 16
    },
    'PB': {
        'a': 8,
        'b': 16,
        'c': 24
    },
    'PVB': {
        'a': 16,
        'b': 24,
        'c': 32
    },
    'PVVB': {
        'a': 24,
        'b': 32,
        'c': None
    }
}



fuzzyRuleBase = {
    'PVB': {
        'PB': 'PVVB',
        'P': 'PVVB',
        'Z': 'PVB',
        'N': 'PB',
        'NB': 'P'
    },
    'PB': {
        'PB': 'PVVB',
        'P': 'PVB',
        'Z': 'PB',
        'N': 'P',
        'NB': 'Z'
    },
    'P': {
        'PB': 'PVB',
        'P': 'PB',
        'Z': 'P',
        'N': 'Z',
        'NB': 'N'
    },
    'Z': {
        'PB': 'PB',
        'P': 'P',
        'Z': 'Z',
        'N': 'N',
        'NB': 'NB'
    },
    'N': {
        'PB': 'P',
        'P': 'Z',
        'Z': 'N',
        'N': 'NB',
        'NB': 'NVB'
    },
    'NB': {
        'PB': 'Z',
        'P': 'N',
        'Z': 'NB',
        'N': 'NVB',
        'NB': 'NVVB'
    },
    'NVB': {
        'PB': 'N',
        'P': 'NB',
        'Z': 'NVB',
        'N': 'NVVB',
        'NB': 'NVVB'
    }
}