export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
                <div class="card" style="width: 300px;">
                    <img style="opacity: 1" class="accordion-collapse collapse show" id ="picture-${data.id}" src="${data.src}" alt="картинка">
                    <div class="card-body ">
                        <h5 class="card-title">${data.title}</h5>
                        <p class="card-text">${data.text}</p>
                        <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Show a sushi cat!</button>
                        <button class="accordeon-button btn btn-primary" id="test-card-${data.id}" data-id="${data.id}" data-bs-toggle="collapse" data-bs-target="#picture-${data.id}"> Collapse a cat</button>
                    </div>
                </div>
            `
        )
    }
    
    addListeners(data, listener) {
        document.getElementById(`click-card-${data.id}`)
            .addEventListener("click", listener)
        document.getElementById(`test-card-${data.id}`)
             .addEventListener("click", listener)
    }
    
    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }
}