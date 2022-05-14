import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DeleteComponent } from './delete/delete.component';
import { InsertComponent } from './insert/insert.component';
import { ProductsComponent } from './products/products.component';
import { UpdateComponent } from './update/update.component';

const routes: Routes = [
    { path: '', component: ProductsComponent },
    { path: 'insert', component: InsertComponent },
    { path: 'update', component: UpdateComponent },
    { path: 'delete', component: DeleteComponent }
];

@NgModule({
    imports: [RouterModule.forRoot(routes)],
    exports: [RouterModule]
})
export class AppRoutingModule { }
