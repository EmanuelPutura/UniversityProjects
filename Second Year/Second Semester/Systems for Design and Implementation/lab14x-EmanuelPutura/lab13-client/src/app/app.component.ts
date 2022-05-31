import {Component, ViewEncapsulation} from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  encapsulation: ViewEncapsulation.None
})
export class AppComponent {
  title = 'lab12-client';
  originalGradient: boolean = false;

  changeBackgroundColor(): void {
    if (this.originalGradient) {
      document.getElementsByTagName("body")[0].style.backgroundImage = "linear-gradient(to top, #cfd9df 0%, #e2ebf0 100%)";
    }
    else {
      document.getElementsByTagName("body")[0].style.backgroundImage = "linear-gradient(0deg, #D9AFD9 0%, #97D9E1 100%)";
    }

    this.originalGradient = !this.originalGradient;
  }
}
