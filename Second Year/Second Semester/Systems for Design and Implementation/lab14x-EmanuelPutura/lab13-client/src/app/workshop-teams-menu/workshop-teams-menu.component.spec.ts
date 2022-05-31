import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkshopTeamsMenuComponent } from './workshop-teams-menu.component';

describe('WorkshopTeamsMenuComponent', () => {
  let component: WorkshopTeamsMenuComponent;
  let fixture: ComponentFixture<WorkshopTeamsMenuComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkshopTeamsMenuComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(WorkshopTeamsMenuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
