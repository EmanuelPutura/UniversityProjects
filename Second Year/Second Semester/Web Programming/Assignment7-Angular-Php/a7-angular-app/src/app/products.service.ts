import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable, of } from 'rxjs';
import { catchError, map, tap } from 'rxjs/operators';

import { Product } from './domain/product';

@Injectable({
    providedIn: 'root'
})
export class ProductsService {
    private backendUrl = 'http://localhost/my-websites/websites/ubb-web-assignment7/server/controller/controller.php';  // url to web api 
    private httpOptions = {
        headers: new HttpHeaders({
            'Content-Type': 'application/x-www-form-urlencoded'
        })
    };

    constructor(private httpClient: HttpClient) {
    }

    fetchProducts(category: string, pageSize: number, pageNumber: number): Observable<Product[]> {
        const requestUrl: string = this.backendUrl + '?func=select&category=' + category + '&pageSize=' + pageSize + '&currentPage=' + pageNumber;
        return this.httpClient.get<Product[]>(requestUrl).pipe(catchError(this.handleError<Product[]>('fetchProducts', [])));
    }

    checkProductId(id: number): Observable<string[]> {
        const requestUrl: string = this.backendUrl + "?func=check&id=" + id;
        return this.httpClient.get<string[]>(requestUrl).pipe(catchError(this.handleError<string[]>('checkProductId', [])));
    }

    addProduct(name: string, category: string, price: number): void {
        const requestBody: string = 'func=insert&productName=' + name + '&productCategory=' + category + '&productPrice=' + price;
        this.httpClient.post<undefined>(this.backendUrl, requestBody, this.httpOptions).pipe(catchError(this.handleError<undefined>('addProduct', undefined))).subscribe();
    }

    deleteProduct(id: number): void {
        this.httpClient.delete(this.backendUrl, {body: {"func": "delete", "productID": id}}).subscribe();
    }

    updateProduct(id: number, name: string, category: string, price: number): void {
        this.httpClient.put(this.backendUrl, {body: {"func": "update", "productID": id, "productName": name, "productCategory": category, "productPrice": price}}).subscribe();
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
