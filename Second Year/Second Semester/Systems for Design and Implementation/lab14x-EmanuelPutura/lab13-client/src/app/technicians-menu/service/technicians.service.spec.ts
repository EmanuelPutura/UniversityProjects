import { TestBed } from '@angular/core/testing';

import { TechniciansService } from './technicians.service';

describe('TechniciansService', () => {
  let service: TechniciansService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(TechniciansService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
