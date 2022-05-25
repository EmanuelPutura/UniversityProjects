import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkshopTeamsInsertComponent } from './workshop-teams-insert.component';

describe('WorkshopTeamsInsertComponent', () => {
  let component: WorkshopTeamsInsertComponent;
  let fixture: ComponentFixture<WorkshopTeamsInsertComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkshopTeamsInsertComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WorkshopTeamsInsertComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
