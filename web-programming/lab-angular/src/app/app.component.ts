import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { ModernarticlesComponent } from './modernarticles/modernarticles.component';
import { LoginpageComponent } from './loginpage/loginpage.component';
import { CommonModule } from '@angular/common';
import { NewarticleformComponent } from './newarticleform/newarticleform.component';
import { GenericService } from './generic.service';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, ModernarticlesComponent, LoginpageComponent, CommonModule, NewarticleformComponent],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  showLogin = false;
  userFullname = "-";
  amIAdmin = false;

  title = 'news-service';

  constructor(private genericService: GenericService) { }

  toggleShowLogin() {
    this.showLogin = !this.showLogin;
  }

  doLogout() {
    this.genericService.logout();
    this.showLogin = true;  // TODO stuff
  }

  handleLogin() {
    this.genericService.getMyNameAndStatus().subscribe(({ name, adminStatus }) => {
      console.log('handlelogin fullname: ' + name);
      if (name != null && name != "null" && name != "") {  // TODO make up your mind
        this.userFullname = name;
        this.amIAdmin = adminStatus;
        this.showLogin = false;
      } else {
        this.showLogin = true;
      }
    });
  }
}
