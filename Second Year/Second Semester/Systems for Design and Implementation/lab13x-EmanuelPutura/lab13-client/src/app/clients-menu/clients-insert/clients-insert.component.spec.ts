import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ClientsInsertComponent } from './clients-insert.component';

describe('ClientsInsertComponent', () => {
  let component: ClientsInsertComponent;
  let fixture: ComponentFixture<ClientsInsertComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ClientsInsertComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ClientsInsertComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
