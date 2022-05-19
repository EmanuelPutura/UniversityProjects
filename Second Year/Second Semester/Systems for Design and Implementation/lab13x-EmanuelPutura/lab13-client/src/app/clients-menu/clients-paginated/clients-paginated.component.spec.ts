import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ClientsPaginatedComponent } from './clients-paginated.component';

describe('ClientsPaginatedComponent', () => {
  let component: ClientsPaginatedComponent;
  let fixture: ComponentFixture<ClientsPaginatedComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ClientsPaginatedComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ClientsPaginatedComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
