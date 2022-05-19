import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansMenuComponent } from './technicians-menu.component';

describe('TechniciansMenuComponent', () => {
  let component: TechniciansMenuComponent;
  let fixture: ComponentFixture<TechniciansMenuComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansMenuComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansMenuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
