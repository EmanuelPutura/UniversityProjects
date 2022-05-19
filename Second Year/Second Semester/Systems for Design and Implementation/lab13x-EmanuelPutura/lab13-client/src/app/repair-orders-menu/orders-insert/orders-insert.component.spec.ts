import { ComponentFixture, TestBed } from '@angular/core/testing';

import { OrdersInsertComponent } from './orders-insert.component';

describe('OrdersInsertComponent', () => {
  let component: OrdersInsertComponent;
  let fixture: ComponentFixture<OrdersInsertComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ OrdersInsertComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(OrdersInsertComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
