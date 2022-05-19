import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TechniciansAssociatedWithListComponent } from './technicians-associated-with-list.component';

describe('TechniciansAssociatedWithListComponent', () => {
  let component: TechniciansAssociatedWithListComponent;
  let fixture: ComponentFixture<TechniciansAssociatedWithListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TechniciansAssociatedWithListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TechniciansAssociatedWithListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
