import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SelectCategoryComponent } from './select-category.component';

describe('SelectCategoryComponent', () => {
  let component: SelectCategoryComponent;
  let fixture: ComponentFixture<SelectCategoryComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SelectCategoryComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(SelectCategoryComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
