import {ProductCardComponent} from "../../components/product-card/index.js";
import {ProductPage} from "../product/index.js";
export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('main-page')
    }

    getHTML() {
        return (
            `
                <div id="main-page" class="d-flex flex-wrap"><div/>
            `
        )
    }

    getData() {
        return [
            {
                id: 1,
                src: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/cute-cat-photos-1593441022.jpg",
                title: "Cute kitten",
                text: "You have never seen a kitten like this before! 1"
            },
            {
                id: 2,
                src: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/cute-photos-of-cats-curled-up-sleeping-1593184773.jpg",
                title: "Cute kitten",
                text: "You have never seen a kitten like this before! 2"
            },
            {
                id: 3,
                src: "https://i.guim.co.uk/img/media/43352be36da0eb156e8551d775a57fadba8ae6d7/0_0_1440_864/master/1440.jpg?width=1200&height=900&quality=85&auto=format&fit=crop&s=184376f73721b565014f1d24e5bf645c",
                title: "Cute kitten",
                text: "You have never seen a kitten like this before! 3"
            },
        ]
    }

    clickCard(e) {
        if (e.target.id === `test-card-${e.target.dataset.id}`) {
            const img = document.querySelector(`#picture-${e.target.dataset.id}`)
        } else {
            const cardId = e.target.dataset.id 
            const productPage = new ProductPage(this.parent, cardId)
            productPage.render()
        }
    }
    
        
    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        
        const data = this.getData()
        data.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot)
            productCard.render(item, this.clickCard.bind(this))
        })
    }
}