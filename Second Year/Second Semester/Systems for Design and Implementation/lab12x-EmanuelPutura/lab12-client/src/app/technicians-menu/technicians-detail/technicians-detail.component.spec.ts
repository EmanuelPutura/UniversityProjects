import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansDetailComponent } from './technicians-detail.component';

describe('TechniciansDetailComponent', () => {
  let component: TechniciansDetailComponent;
  let fixture: ComponentFixture<TechniciansDetailComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansDetailComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansDetailComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
