import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ClientsSortedFilteredListComponent } from './clients-sorted-filtered-list.component';

describe('ClientsSortedFilteredListComponent', () => {
  let component: ClientsSortedFilteredListComponent;
  let fixture: ComponentFixture<ClientsSortedFilteredListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ClientsSortedFilteredListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ClientsSortedFilteredListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
