import { CommonModule } from '@angular/common';
import { Component, EventEmitter, Output } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { GenericService } from '../generic.service';

@Component({
  selector: 'app-loginpage',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './loginpage.component.html',
  styleUrl: './loginpage.component.css'
})
export class LoginpageComponent {
  username: string = "";
  password: string = "";

  @Output() loginEvent = new EventEmitter<void>();

  constructor(private genericService: GenericService) { }

  doLogin() {
    this.genericService.login(this.username, this.password);

    this.loginEvent.emit();

    // .subscribe(response => {
    //   if (response != null) {
    //     const { fullname, isAdmin } = response;
    //     console.log('will emit with ' + fullname);

    //     this.loginEvent.emit({ fullname, isAdmin });
    //   } else {
    //     console.log('no response...');
    //   }
    // });
  }
}
