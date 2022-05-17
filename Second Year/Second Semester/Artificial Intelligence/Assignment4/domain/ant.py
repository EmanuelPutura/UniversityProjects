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


class AntWithAvailableEnergy(Ant):
    def __init__(self, startSensor, sensorFitness, availableEnergy):
        super().__init__(startSensor, sensorFitness)
        self.__availableEnergy = availableEnergy

    @property
    def availableEnergy(self):
        return self.__availableEnergy

    def evaluateAnt(self):
        return (1 / self.fitness) * self.computeConsumedEnergy()

    def computeConsumedEnergy(self):
        totalEnergy = 0
        for sensor in self.sensorsPath:
            totalEnergy += sensor.energy

        return totalEnergy

    def addSensor(self, sensor, sensorFitness):
        super().addSensor(sensor, sensorFitness)
        if self.__availableEnergy - sensor.energy < 0:
            sensor.energy = self.__availableEnergy
            self.__availableEnergy = 0
        else:
            self.__availableEnergy -= sensor.energy
