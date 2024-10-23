import { Component } from '@angular/core';
import { GenericService } from '../generic.service';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-newarticleform',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './newarticleform.component.html',
  styleUrl: './newarticleform.component.css'
})
export class NewarticleformComponent {
  authorInput: string = "";
  textInput: string = "";
  categoryInput: string = "";
  dateInput: string = "";
  titleInput: string = "";

  constructor(private genericService: GenericService) { }

  doAdd() {
    let username: string = sessionStorage.getItem('username') || "";
    let password: string = sessionStorage.getItem('password') || "";

    const errors = this.validateInputs();
    if (errors === "") {
      this.genericService.addArticle(
        this.authorInput,
        this.titleInput,
        this.textInput,
        this.categoryInput,
        this.dateInput
      );
    } else {
      alert("Invalid inputs: " + errors);
    }
  }

  validateInputs() {
    let errors = "";

    if (this.authorInput === "")
      errors += "author is empty; ";
    if (this.textInput.length < 3)
      errors += "text must be at least 3 chars long; ";
    if (this.titleInput === "")
      errors += "title is empty; ";
    if (this.categoryInput === "")
      errors += "category is empty; ";

    let dateRegex = /^\d{4}-\d{2}-\d{2}$/;
    if (!dateRegex.test(this.dateInput))
      errors += "date must be in format yyyy-mm-dd; "

    return errors;
  }
}
