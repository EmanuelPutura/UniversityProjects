import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesDetailComponent } from './devices-detail.component';

describe('DevicesDetailComponent', () => {
  let component: DevicesDetailComponent;
  let fixture: ComponentFixture<DevicesDetailComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesDetailComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesDetailComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
