import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkshopTeamsDetailComponent } from './workshop-teams-detail.component';

describe('WorkshopTeamsDetailComponent', () => {
  let component: WorkshopTeamsDetailComponent;
  let fixture: ComponentFixture<WorkshopTeamsDetailComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkshopTeamsDetailComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WorkshopTeamsDetailComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
