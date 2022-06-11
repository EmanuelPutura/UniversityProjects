import { TestBed } from '@angular/core/testing';

import { SensorsService } from './sensors.service';

describe('SensorsService', () => {
  let service: SensorsService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(SensorsService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
