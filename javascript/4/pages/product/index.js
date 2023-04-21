import {ProductComponent} from "../../components/product/index.js";
import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";

<<<<<<< HEAD
=======

import {ajax} from "../../modules/ajax.js";
import {urls} from "../../modules/urls.js";

>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d
export class ProductPage {
    constructor(parent, id) {
        this.parent = parent
        this.id = id
    }

    getData() {
<<<<<<< HEAD
        return {
            id: 1,
            src: "https://www.mythirtyspot.com/wp-content/uploads/2014/09/Screen-Shot-2014-09-18-at-10.19.29-PM-1024x712.png",
            title: `Cute kitten! ${this.id}`,
            text: "sushi cat"
        }
    }
=======
        ajax.post(urls.getUserInfo(this.id), (data) => {
            this.renderData(data.response)
        })
    }

    renderData(item) {
        const product = new ProductComponent(this.pageRoot)
        product.render(item[0])
    }
    
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <div id="product-page"></div>
            `
        )
    }

    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }

    render() {
<<<<<<< HEAD
    this.parent.innerHTML = ''
    const html = this.getHTML()
    this.parent.insertAdjacentHTML('beforeend', html)

    const backButton = new BackButtonComponent(this.pageRoot)
    backButton.render(this.clickBack.bind(this))

    const data = this.getData()
    const stock = new ProductComponent(this.pageRoot)
    stock.render(data)
}
=======
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
    
        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
        
        this.getData()
    }
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d
}