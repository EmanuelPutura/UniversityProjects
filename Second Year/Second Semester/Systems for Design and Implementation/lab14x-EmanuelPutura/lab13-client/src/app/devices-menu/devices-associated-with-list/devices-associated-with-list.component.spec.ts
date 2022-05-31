import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DevicesAssociatedWithListComponent } from './devices-associated-with-list.component';

describe('DevicesAssociatedWithListComponent', () => {
  let component: DevicesAssociatedWithListComponent;
  let fixture: ComponentFixture<DevicesAssociatedWithListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DevicesAssociatedWithListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DevicesAssociatedWithListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
