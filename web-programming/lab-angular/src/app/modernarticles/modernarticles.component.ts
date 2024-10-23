import { Component, Input, OnInit } from '@angular/core';
import { Article } from '../article';
import { CommonModule } from '@angular/common';
import { GenericService } from '../generic.service';
import { Category } from '../category';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-modernarticles',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './modernarticles.component.html',
  styleUrl: './modernarticles.component.css'
})
export class ModernarticlesComponent implements OnInit {
  @Input() amIAdmin: boolean = true;
  allArticles: Article[] = [];
  allCategories: Category[] = [];
  selectedCategory: string = "society";
  startDate: string = "1000-01-01";
  endDate: string = "2500-12-31";
  showUpdate: boolean[] = [];
  newTitleInput: string[] = [];
  newTextInput: string[] = [];
  previousCategory: string = "-";
  previousStart: string = "-";
  previousEnd: string = "-";

  constructor(private genericService: GenericService) { }

  ngOnInit(): void {
    this.getArticles();
    this.getCategories();
  }

  getArticles(): void {
    this.genericService.fetchArticles(this.selectedCategory, this.startDate, this.endDate)
      .subscribe(articles => {
        this.allArticles = articles;
        this.initializeInputs();
      });
  }

  getCategories(): void {
    this.genericService.fetchCategories()
      .subscribe(categories => this.allCategories = categories);
  }

  initializeInputs(): void {
    this.newTitleInput = this.allArticles.map(article => article.articleTitle);
    this.newTextInput = this.allArticles.map(article => article.articleText);
    this.showUpdate = this.allArticles.map(() => false);
  }

  toggleShowUpdate(articleIndexInUi: number) {
    this.showUpdate[articleIndexInUi] = !this.showUpdate[articleIndexInUi];
  }

  onSelect(article: Article): void {
    console.log(article.articleTitle + " is selected.");
  }

  onCategoryChange(selectedValue: any) {
    this.previousCategory = this.selectedCategory;
    this.previousStart = this.startDate;
    this.previousEnd = this.endDate;

    console.log('changed categ to ' + selectedValue.target.value);
    this.selectedCategory = selectedValue.target.value;

    this.getArticles();
  }

  onStartDateChange(theDate: any) {
    this.previousCategory = this.selectedCategory;
    this.previousStart = this.startDate;
    this.previousEnd = this.endDate;


    this.startDate = theDate.target.value;

    this.getArticles();
  }

  onEndDateChange(theDate: any) {
    this.previousCategory = this.selectedCategory;
    this.previousStart = this.startDate;
    this.previousEnd = this.endDate;

    this.endDate = theDate.target.value;

    this.getArticles();
  }

  doDelete(articleId: number) {
    console.log('will delete (ts)');

    if (confirm("Do you really want to delete the article?")) {
      let username: string = sessionStorage.getItem('username') || "";
      let password: string = sessionStorage.getItem('password') || "";

      this.genericService.doDelete(articleId);
    }
  }

  doUpdate(articleId: number, articleUiIndex: number) {
    console.log('will uipdate (ts)');

    this.genericService.doUpdate(articleId,
      this.newTitleInput[articleUiIndex], this.newTextInput[articleUiIndex]);
  }

  something() {
    console.log('jno t');
  }
}
