import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansListComponent } from './technicians-list.component';

describe('TechniciansListComponent', () => {
  let component: TechniciansListComponent;
  let fixture: ComponentFixture<TechniciansListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
