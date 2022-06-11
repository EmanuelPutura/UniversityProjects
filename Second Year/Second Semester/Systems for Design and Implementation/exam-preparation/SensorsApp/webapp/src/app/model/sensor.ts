export interface Sensor {
  id: number;
  name: string;
  measurement: number;
  time: { hour: number, minute: number, second: number };
}
