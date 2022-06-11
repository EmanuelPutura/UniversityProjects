import { Component, OnInit } from '@angular/core';
import {SensorsService} from "../service/sensors.service";
import {Sensor} from "../model/sensor";
import {Router} from "@angular/router";

@Component({
  selector: 'app-test-component',
  templateUrl: './test-component.component.html',
  styleUrls: ['./test-component.component.css']
})
export class TestComponentComponent implements OnInit {
  sensors: Array<Sensor>;

  constructor(private sensorsService: SensorsService, private router: Router) { }

  ngOnInit(): void {
    const thisObj = this;
    setInterval(function() {thisObj.getSensors()}, 1000);
    // this.getSensors();
  }

  getSensors(): void {
    this.sensorsService.getSensors()
      .subscribe(
        sensors => {
          this.sensors = sensors
        },
      );
  }
}
