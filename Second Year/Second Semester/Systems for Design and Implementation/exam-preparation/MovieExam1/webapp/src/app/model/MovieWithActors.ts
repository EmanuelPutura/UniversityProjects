import {Actor} from "./Actor";

export interface MovieWithActors {
  id: number;
  title: string;
  year: number;
  actors: Actor[];
}
