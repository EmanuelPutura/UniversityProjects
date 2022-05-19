import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesInsertComponent } from './devices-insert.component';

describe('DevicesInsertComponent', () => {
  let component: DevicesInsertComponent;
  let fixture: ComponentFixture<DevicesInsertComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesInsertComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesInsertComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
