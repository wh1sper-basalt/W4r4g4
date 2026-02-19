document.addEventListener('DOMContentLoaded', function() {
    const currentPage = window.location.pathname.split('/').pop();
    const navLinks = document.querySelectorAll('.nav-link');

    navLinks.forEach(link => {
        if (link.getAttribute('href') === currentPage) {
            link.classList.add('active');
        }
    });

    // Подсветка для блоков с Emmet
    const emmetBlocks = document.querySelectorAll('.emmet-code');
    emmetBlocks.forEach(block => {
        block.addEventListener('mouseenter', function() {
            this.style.backgroundColor = '#3d3d3d';
            this.style.transition = '0.3s';
        });
        block.addEventListener('mouseleave', function() {
            this.style.backgroundColor = '#2d2d2d';
        });
    });

    // Интерактивность для демонстрационных блоков
    const demoBlocks = document.querySelectorAll('.structure-block, .advantage-item, .review-card');
    demoBlocks.forEach(block => {
        block.addEventListener('click', function() {
            const structure = this.innerHTML.split('<')[0].trim();
            alert('Структурный блок: ' + (structure || 'Элемент структуры'));
        });
    });
});