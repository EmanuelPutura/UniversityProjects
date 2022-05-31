import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansInsertComponent } from './technicians-insert.component';

describe('TechniciansInsertComponent', () => {
  let component: TechniciansInsertComponent;
  let fixture: ComponentFixture<TechniciansInsertComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansInsertComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansInsertComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
