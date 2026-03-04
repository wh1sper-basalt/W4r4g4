// Получение элементов
const a = document.getElementById('a');
const b = document.getElementById('b');
const c = document.getElementById('c');
const result = document.getElementById('result');
const runTestsBtn = document.getElementById('run-tests');

// Тестовые случаи (ровно 7 как в таблице)
const tests = [
    {a: 1, b: 1, c: -2, desc: "D > 0"},
    {a: 1, b: 2, c: 1, desc: "D = 0"},
    {a: 2, b: 1, c: 2, desc: "D < 0"},
    {a: 0, b: 0, c: 0, desc: "a=0, b=0, c=0"},
    {a: 0, b: 0, c: 2, desc: "a=0, b=0, c≠0"},
    {a: 0, b: 2, c: 1, desc: "a=0, b≠0"},
    {a: 2, b: 1, c: 0, desc: "a≠0, b≠0, c=0"}
];

// Функция решения уравнения
function solve() {
    const aVal = parseFloat(a.value);
    const bVal = parseFloat(b.value);
    const cVal = parseFloat(c.value);

    let solution;

    // Проверка особых случаев
    if (aVal === 0) {
        if (bVal === 0) {
            if (cVal === 0) {
                solution = "x - любое число";
            } else {
                solution = "Нет решения (неправильное уравнение)";
            }
        } else {
            // Линейное уравнение
            const x = -cVal / bVal;
            solution = `x = ${x}`;
        }
    } else {
        // Квадратное уравнение
        const D = bVal * bVal - 4 * aVal * cVal;

        if (D > 0) {
            const x1 = (-bVal + Math.sqrt(D)) / (2 * aVal);
            const x2 = (-bVal - Math.sqrt(D)) / (2 * aVal);
            solution = `x₁ = ${x1.toFixed(2)}, x₂ = ${x2.toFixed(2)}`;
        } else if (D === 0) {
            const x = -bVal / (2 * aVal);
            solution = `x₁ = x₂ = ${x.toFixed(2)}`;
        } else {
            solution = "Нет действительных корней";
        }
    }

    result.textContent = solution;
}

// Функция запуска тестов
function runTests() {
    const tableBody = document.querySelector('.test-table tbody');
    tableBody.innerHTML = '';

    tests.forEach((test, i) => {
        const row = tableBody.insertRow();

        // Номер теста
        row.insertCell(0).textContent = i + 1;

        // Описание
        row.insertCell(1).textContent = test.desc;

        // Коэффициенты
        row.insertCell(2).textContent = test.a;
        row.insertCell(3).textContent = test.b;
        row.insertCell(4).textContent = test.c;

        // Результат
        let solution;
        if (test.a === 0) {
            if (test.b === 0) {
                if (test.c === 0) {
                    solution = "x - любое число";
                } else {
                    solution = "Нет решения";
                }
            } else {
                const x = -test.c / test.b;
                solution = `x = ${x}`;
            }
        } else {
            const D = test.b * test.b - 4 * test.a * test.c;
            if (D > 0) {
                const x1 = (-test.b + Math.sqrt(D)) / (2 * test.a);
                const x2 = (-test.b - Math.sqrt(D)) / (2 * test.a);
                solution = `x₁ = ${x1}, x₂ = ${x2}`;
            } else if (D === 0) {
                const x = -test.b / (2 * test.a);
                solution = `x₁ = x₂ = ${x}`;
            } else {
                solution = "Нет действительных корней";
            }
        }

        row.insertCell(5).textContent = solution;
    });

    document.querySelector('.test-results').textContent = "✓ 7 тестов выполнено";
}

// Назначаем обработчики
document.getElementById('solve').onclick = solve;
runTestsBtn.onclick = runTests;

// Запускаем тесты при загрузке
runTests();