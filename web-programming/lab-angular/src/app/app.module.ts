import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { ModernarticlesComponent } from './modernarticles/modernarticles.component';
import { LoginpageComponent } from './loginpage/loginpage.component';
import { CommonModule } from '@angular/common';

@NgModule({
    declarations: [
        AppComponent,
    ],
    imports: [
        BrowserModule,
        HttpClientModule,
        FormsModule,
        ModernarticlesComponent,
        LoginpageComponent,
        CommonModule,
    ],
    providers: [],
    bootstrap: [AppComponent]
})
export class AppModule { }
