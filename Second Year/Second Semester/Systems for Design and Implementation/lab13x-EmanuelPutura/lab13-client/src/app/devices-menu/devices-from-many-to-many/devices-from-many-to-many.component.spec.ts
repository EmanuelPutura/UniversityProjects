import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesFromManyToManyComponent } from './devices-from-many-to-many.component';

describe('DevicesFromManyToManyComponent', () => {
  let component: DevicesFromManyToManyComponent;
  let fixture: ComponentFixture<DevicesFromManyToManyComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesFromManyToManyComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesFromManyToManyComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
