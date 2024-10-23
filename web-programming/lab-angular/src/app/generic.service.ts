import { HttpClient, HttpHeaders, HttpParams, HttpResponse } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, catchError, of } from 'rxjs';
import { Article } from './article';
import { Category } from './category';

@Injectable({
  providedIn: 'root'
})
export class GenericService {
  private backendUrl = 'http://localhost/facultate/web/php_hw/controller/controller.php';
  private loginUrl = 'http://localhost/facultate/web/php_hw/do_login2.php';
  private logoutUrl = 'http://localhost/facultate/web/php_hw/do_logout.php';

  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };

  constructor(private http: HttpClient) { }

  fetchArticles(category: string, startDate: string, endDate: string): Observable<Article[]> {
    return this.http.get<Article[]>(this.backendUrl +
      '?action=loadArticles&category=' + category + '&startDate=' + startDate + '&endDate=' + endDate)
      .pipe(catchError(this.handleError<Article[]>('fetchStudents', []))
      );
  }

  fetchCategories(): Observable<Category[]> {
    return this.http.get<Category[]>(this.backendUrl +
      '?action=getAllCategories')
      .pipe(catchError(this.handleError<Category[]>('fetchCategories', []))
      );
  }

  login(username: string, password: string) {
    console.log('will login');

    // return this.http.get<{fullname: string, isAdmin: boolean}>(this.backendUrl +
    //   '?action=getNameAndAdminStatusByCredentials&username=' + username + '&password=' + password);

    const formData = new FormData();
    formData.append('user-input', username);
    formData.append('password', password);

    this.http.post<any>(this.loginUrl, formData).subscribe(response => {
      console.log('login response: ' + JSON.stringify(response));
    });
  }

  logout() {
    this.http.post<any>(this.logoutUrl, null).subscribe(response => {
      console.log('logout response: ' + JSON.stringify(response));
    });
  }

  addArticle(author: string, title: string, text: string, category: string, date: string) {
    console.log('will add article');
    const formData = new FormData();
    formData.append('action', 'postNewArticle');
    formData.append('title', title);
    formData.append('text', text);
    formData.append('author', author);
    formData.append('category', category);
    formData.append('date', date);

    let response = this.http.post<any>(this.backendUrl, formData).subscribe(response => {
      console.log(response);
    })
  }

  doDelete(articleId: number) {
    console.log('will do delete');
    const formData = new FormData();
    formData.append('action', 'deleteArticle');
    formData.append('articleId', articleId.toString());
    let response = this.http.post<any>(this.backendUrl, formData).subscribe(response => {
      console.log(response);
    })
  }

  doUpdate(articleId: number, newTitle: string, newText: string) {
    console.log('will do update');
    const formData = new FormData();
    formData.append('action', 'updateArticle');
    formData.append('articleId', articleId.toString());
    formData.append('newTitle', newTitle);
    formData.append('newText', newText);

    let response = this.http.post<any>(this.backendUrl, formData).subscribe(response => {
      console.log("post response: " + response);
    })
  }

  getMyNameAndStatus(): Observable<{ name: string, adminStatus: boolean }> {
    return this.http.get<{ name: string, adminStatus: boolean }>(this.backendUrl +
      '?action=getMyNameAndAdminStatus')
      .pipe(catchError(this.handleError<{ name: string, adminStatus: boolean }>('getMyNameAndAdminStatus', { name: "error", adminStatus: false }))
      );
  }

  /**
  * Handle Http operation that failed.
  * Let the app continue.
  * @param operation - name of the operation that failed
  * @param result - optional value to return as the observable result
  */
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {

      // TODO: send the error to remote logging infrastructure
      console.error(error); // log to console instead

      // Let the app keep running by returning an empty result.
      return of(result as T);
    };
  }
}
