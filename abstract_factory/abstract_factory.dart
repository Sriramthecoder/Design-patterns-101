// Define abstract class for AppBar widget
abstract class AppBarWidget {
  void display();
}

// Define abstract class for Button widget
abstract class ButtonWidget {
  void display();
}

// Create a class for material widget to implement the AppBarWidget
class MaterialAppBarWidget implements AppBarWidget {
  @override
  void display() => print("Material App Bar Widget Displayed");
}

// Create a class for material widget to implement the ButtonWidget
class MaterialButtonWidget implements ButtonWidget {
  @override
  void display() => print("Material Button Widget Displayed");
}

// Create a class for Cupertino widget to implement the AppBarWidget
class CupertinoAppBarWidget implements AppBarWidget {
  @override
  void display() => print("Cupertino App Bar Widget Displayed");
}

// Create a class for Cupertino widget to implement the ButtonWidget
class CupertinoButtonWidget implements ButtonWidget {
  @override
  void display() => print("Cupertino Button Widget Displayed");
}

// Create an abstract class to have widgetFactory 
abstract class WidgetFactory {
  AppBarWidget createAppBar();
  ButtonWidget createButton();
}

// Create a MaterialWidgetFactory which implements WidgetFactory to make a seperate class for Material components.
class MaterialWidgetFactory implements WidgetFactory {
  @override
  AppBarWidget createAppBar() => MaterialAppBarWidget();

  @override
  ButtonWidget createButton() => MaterialButtonWidget();
}

// Create a MaterialWidgetFactory which implements WidgetFactory to make a seperate class for Material components.
class CupertinoWidgetFactory implements WidgetFactory {
  @override
  AppBarWidget createAppBar() => CupertinoAppBarWidget();

  @override
  ButtonWidget createButton() => CupertinoButtonWidget();
}

// Create a class named App to create the factory 
class App {
  final WidgetFactory factory;
  App(this.factory);

  void build() {
    factory.createAppBar().display();
    factory.createButton().display();
  }
}

// Main function
void main() {
  WidgetFactory factory = CupertinoWidgetFactory();
  App app = App(factory);

  // Build the app
  app.build();
}

