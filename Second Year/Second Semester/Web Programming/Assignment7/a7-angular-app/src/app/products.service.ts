import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable, of } from 'rxjs';
import { catchError, map, tap } from 'rxjs/operators';

import { Product } from './domain/product';

@Injectable({
    providedIn: 'root'
})
export class ProductsService {
    private backendUrl = 'http://localhost/my-websites/websites/ubb-web-assignment6/server/controller/controller.php';  // url to web api 
    httpOptions = {
        headers: new HttpHeaders({
            'Content-Type': 'application/json'
        })
    };

    constructor(private httpClient: HttpClient) {
    }

    fetchProducts(category: string, pageSize: number, pageNumber: number): Observable<Product[]> {
        const requestUrl: string = this.backendUrl + '?func=select&category=' + category + '&pageSize=' + pageSize + '&currentPage=' + pageNumber;
        return this.httpClient.get<Product[]>(requestUrl).pipe(catchError(this.handleError<Product[]>('fetchProducts', [])));
    }

    /**
    * Handle the http operation that failed.
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
