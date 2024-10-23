import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NewarticleformComponent } from './newarticleform.component';

describe('NewarticleformComponent', () => {
  let component: NewarticleformComponent;
  let fixture: ComponentFixture<NewarticleformComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [NewarticleformComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(NewarticleformComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
