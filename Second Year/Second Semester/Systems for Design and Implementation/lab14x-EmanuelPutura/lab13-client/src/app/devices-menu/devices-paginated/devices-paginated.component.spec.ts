import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesPaginatedComponent } from './devices-paginated.component';

describe('DevicesPaginatedComponent', () => {
  let component: DevicesPaginatedComponent;
  let fixture: ComponentFixture<DevicesPaginatedComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesPaginatedComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesPaginatedComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
