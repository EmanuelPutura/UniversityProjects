import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansPaginatedComponent } from './technicians-paginated.component';

describe('TechniciansPaginatedComponent', () => {
  let component: TechniciansPaginatedComponent;
  let fixture: ComponentFixture<TechniciansPaginatedComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansPaginatedComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansPaginatedComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
