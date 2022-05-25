import { TestBed } from '@angular/core/testing';

import { WorkshopTeamsService } from './workshop-teams.service';

describe('WorkshopTeamsService', () => {
  let service: WorkshopTeamsService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(WorkshopTeamsService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
