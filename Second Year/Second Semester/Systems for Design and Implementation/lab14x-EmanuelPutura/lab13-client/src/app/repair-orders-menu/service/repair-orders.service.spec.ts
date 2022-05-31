import { TestBed } from '@angular/core/testing';

import { RepairOrdersService } from './repair-orders.service';

describe('RepairOrdersService', () => {
  let service: RepairOrdersService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(RepairOrdersService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
