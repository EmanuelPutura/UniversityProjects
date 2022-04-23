class Ant:
    def __init__(self, startSensor, sensorFitness):
        self.__sensorsPath = [startSensor]
        self.__fitness = sensorFitness

    @property
    def sensorsPath(self):
        return self.__sensorsPath

    @property
    def lastSensor(self):
        return self.__sensorsPath[-1]

    @property
    def fitness(self):
        return self.__fitness

    def addSensor(self, sensor, sensorFitness):
        self.__sensorsPath.append(sensor)
        self.__fitness += sensorFitness
