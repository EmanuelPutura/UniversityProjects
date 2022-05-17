import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ClientsMenuComponent } from './clients-menu.component';

describe('ClientsMenuComponent', () => {
  let component: ClientsMenuComponent;
  let fixture: ComponentFixture<ClientsMenuComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ClientsMenuComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ClientsMenuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
