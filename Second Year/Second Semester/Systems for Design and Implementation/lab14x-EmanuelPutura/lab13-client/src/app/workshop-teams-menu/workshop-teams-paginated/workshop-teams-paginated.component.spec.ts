import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkshopTeamsPaginatedComponent } from './workshop-teams-paginated.component';

describe('WorkshopTeamsPaginatedComponent', () => {
  let component: WorkshopTeamsPaginatedComponent;
  let fixture: ComponentFixture<WorkshopTeamsPaginatedComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkshopTeamsPaginatedComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WorkshopTeamsPaginatedComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
