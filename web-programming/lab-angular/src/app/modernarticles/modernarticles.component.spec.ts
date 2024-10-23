import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ModernarticlesComponent } from './modernarticles.component';

describe('ModernarticlesComponent', () => {
  let component: ModernarticlesComponent;
  let fixture: ComponentFixture<ModernarticlesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [ModernarticlesComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(ModernarticlesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
