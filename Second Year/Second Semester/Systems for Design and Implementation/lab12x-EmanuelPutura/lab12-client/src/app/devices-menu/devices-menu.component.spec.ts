import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesMenuComponent } from './devices-menu.component';

describe('DevicesMenuComponent', () => {
  let component: DevicesMenuComponent;
  let fixture: ComponentFixture<DevicesMenuComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesMenuComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesMenuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
