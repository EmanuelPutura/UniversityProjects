import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkshopTeamsListComponent } from './workshop-teams-list.component';

describe('WorkshopTeamsListComponent', () => {
  let component: WorkshopTeamsListComponent;
  let fixture: ComponentFixture<WorkshopTeamsListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkshopTeamsListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WorkshopTeamsListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
