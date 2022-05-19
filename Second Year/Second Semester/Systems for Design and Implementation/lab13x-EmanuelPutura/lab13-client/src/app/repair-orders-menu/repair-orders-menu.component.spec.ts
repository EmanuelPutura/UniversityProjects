import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RepairOrdersMenuComponent } from './repair-orders-menu.component';

describe('RepairOrdersMenuComponent', () => {
  let component: RepairOrdersMenuComponent;
  let fixture: ComponentFixture<RepairOrdersMenuComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RepairOrdersMenuComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(RepairOrdersMenuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
