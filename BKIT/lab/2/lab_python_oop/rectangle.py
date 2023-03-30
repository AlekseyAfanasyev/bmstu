from lab_python_oop.figure import Figure
from lab_python_oop.figure_color import Figure_color
class Rectangle(Figure):
    FIGURE_TYPE = "Прямоугольник"

    @classmethod
    def get_figure_type(cls):
        return cls.FIGURE_TYPE

    def __init__(self, width, height, color):
        self._figure_color = Figure_color()
        self._width = width
        self._height = height
        self._figure_color.colorproperty = color

    def get_area(self):
        return self._width * self._height

    def __repr__(self):
        return '{} {} цвета шириной {} и высотой {} площадью {}.'.format(
            Rectangle.get_figure_type(),
            self._figure_color.colorproperty,
            self._width,
            self._height,
            self.get_area()
        )